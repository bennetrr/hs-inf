use crate::utils::error::Error;
use actix_web::body::MessageBody;
use actix_web::dev::{ServiceRequest, ServiceResponse};
use actix_web::error::{ErrorInternalServerError, ErrorUnauthorized};
use actix_web::http::header::AUTHORIZATION;
use actix_web::middleware::Next;
use actix_web::{FromRequest, HttpMessage, HttpRequest};
use jsonwebtoken::{Algorithm, DecodingKey, EncodingKey, Header, Validation, decode, encode};
use serde::{Deserialize, Serialize};
use std::future::{Ready, ready};
use std::sync::OnceLock;
use std::time::{SystemTime, UNIX_EPOCH};

const ISSUER: &str = "craftmine-authentication-service";
const TOKEN_TTL_SECS: u64 = 60 * 60;

#[derive(Clone, Debug, Serialize, Deserialize)]
pub(crate) struct Claims {
    pub sub: String,
    pub name: String,
    pub iss: String,
    pub iat: u64,
    pub exp: u64,
}

impl FromRequest for Claims {
    type Error = actix_web::Error;
    type Future = Ready<Result<Self, Self::Error>>;

    fn from_request(req: &HttpRequest, _: &mut actix_web::dev::Payload) -> Self::Future {
        ready(req.extensions().get::<Claims>().cloned().ok_or_else(|| {
            ErrorInternalServerError("Claims missing; route is not wrapped in `authenticated`")
        }))
    }
}

fn private_key() -> Result<&'static EncodingKey, Error> {
    static KEY: OnceLock<Result<EncodingKey, String>> = OnceLock::new();
    KEY.get_or_init(|| {
        let pem = "-----BEGIN PRIVATE KEY-----
                 MC4CAQAwBQYDK2VwBCIEIECBHmAAtAMSVpo+Xi+8XByYo5ylWpfO6Gctjgvy5FAA
                 -----END PRIVATE KEY-----";
        EncodingKey::from_ed_pem(pem.as_bytes()).map_err(|e| e.to_string())
    })
    .as_ref()
    .map_err(|e| Error::Unexpected(e.clone()))
}

fn public_key() -> Result<&'static DecodingKey, Error> {
    static KEY: OnceLock<Result<DecodingKey, String>> = OnceLock::new();
    KEY.get_or_init(|| {
        let pem = "-----BEGIN PUBLIC KEY-----
                MCowBQYDK2VwAyEA4IgBDcKuoA4Y7bzYRvj8a0624WjfDSb3SBo1BYQpYn4=
                -----END PUBLIC KEY-----";
        DecodingKey::from_ed_pem(pem.as_bytes()).map_err(|e| e.to_string())
    })
    .as_ref()
    .map_err(|e| Error::Unexpected(e.clone()))
}

pub(crate) fn create_jwt(id: String, name: String) -> Result<String, Error> {
    let now = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .map_err(|e| Error::Unexpected(e.to_string()))?
        .as_secs();

    let claims = Claims {
        sub: id,
        name,
        iss: ISSUER.to_string(),
        iat: now,
        exp: now + TOKEN_TTL_SECS,
    };

    encode(&Header::new(Algorithm::EdDSA), &claims, private_key()?)
        .map_err(|e| Error::Unexpected(e.to_string()))
}

pub(crate) fn verify_jwt(token: &str) -> Result<Claims, Error> {
    let mut validation = Validation::new(Algorithm::EdDSA);
    validation.set_issuer(&[ISSUER]);
    decode::<Claims>(token, public_key()?, &validation)
        .map(|data| data.claims)
        .map_err(|_| Error::Authorization())
}

pub(crate) async fn authenticated(
    req: ServiceRequest,
    next: Next<impl MessageBody>,
) -> Result<ServiceResponse<impl MessageBody>, actix_web::Error> {
    let token = req
        .headers()
        .get(AUTHORIZATION)
        .and_then(|h| h.to_str().ok())
        .and_then(|h| h.strip_prefix("Bearer "))
        .ok_or_else(|| ErrorUnauthorized("missing or malformed Authorization header"))?;

    let claims = verify_jwt(token).map_err(|_| ErrorUnauthorized("invalid token"))?;
    req.extensions_mut().insert(claims);

    next.call(req).await
}
