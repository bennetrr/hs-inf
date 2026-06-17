use crate::utils::jwt::authenticated;
use actix_web::middleware::from_fn;
use actix_web::{App, HttpServer, web};
use sea_orm::Database;
use std::env::var;
use std::io::Write;
use flexi_logger::{Age, Cleanup, Criterion, Duplicate, FileSpec, Naming};
use log::logger;
use opentelemetry_appender_tracing::layer::OpenTelemetryTracingBridge;
use opentelemetry_otlp::{LogExporterBuilder, Protocol, WithExportConfig};
use opentelemetry_sdk::logs::{BatchLogProcessor, SdkLoggerProvider};
use opentelemetry_sdk::Resource;
use tracing_subscriber::Layer;
use tracing_subscriber::layer::SubscriberExt;
use tracing_subscriber::util::SubscriberInitExt;

pub mod endpoints;
pub(crate) mod entities;
pub(crate) mod utils;

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    // Set up logging
    // Task 2.1
    env_logger::init();

    // Task 2.3
    // env_logger::builder()
    //     .filter_level(log::LevelFilter::Info)
    //     .parse_default_env()
    //     .init();

    // Task 2.5
    // env_logger::builder()
    //     .filter_level(log::LevelFilter::Info)
    //     .format(|buf, record| {
    //         let ts = buf.timestamp();
    //         let level = record.level();
    //         let target = record.target();
    //         let message = record.args();
    //
    //         writeln!(buf, "[{ts} | {level} | {target}] {message}")
    //     })
    //     .parse_default_env()
    //     .init();

    // Task 3.1
    // flexi_logger::Logger::try_with_str("debug")
    //     .expect("Failed to initialize logger")
    //     .start()
    //     .expect("Failed to start logger");

    // Task 3.2
    // flexi_logger::Logger::try_with_str("debug")
    //     .expect("Failed to initialize logger")
    //     .log_to_file(FileSpec::default().directory("logs"))
    //     .duplicate_to_stderr(Duplicate::Info)
    //     .rotate(Criterion::AgeOrSize(Age::Day, 10000), Naming::Timestamps, Cleanup::KeepLogFiles(20))
    //     .start()
    //     .expect("Failed to start logger");

    // Task 3.3
    // flexi_logger::Logger::try_with_str("debug")
    //     .expect("Failed to initialize logger")
    //     .log_to_file(FileSpec::default().directory("logs"))
    //     .duplicate_to_stderr(Duplicate::Info)
    //     .rotate(Criterion::AgeOrSize(Age::Day, 10000), Naming::Timestamps, Cleanup::KeepLogFiles(20))
    //     .format(|buf, ts, record| {
    //         let ts = ts.format("%Y-%m-%dT%H:%M:%SZ");
    //         let level = record.level();
    //         let target = record.target();
    //         let message = record.args();
    //
    //         write!(buf, "[{ts} | {level} | {target}] {message}")
    //     })
    //     .start()
    //     .expect("Failed to start logger");

    // Task 4.1
    // let exporter = LogExporterBuilder::new()
    //     .with_http()
    //     .with_endpoint("http://localhost:65431/v1/logs")
    //     .with_protocol(Protocol::HttpBinary)
    //     .build()
    //     .expect("Could not build OTLP exporter");
    //
    // let logger_provider = SdkLoggerProvider::builder()
    //     .with_log_processor(BatchLogProcessor::builder(exporter).build())
    //     .build();
    //
    // let otel_layer = OpenTelemetryTracingBridge::new(&logger_provider);
    // tracing_subscriber::registry()
    //     .with(tracing_subscriber::fmt::layer()
    //         .with_writer(std::io::stderr)
    //         .with_filter(tracing_subscriber::EnvFilter::try_from_default_env().unwrap_or_else(|_| tracing_subscriber::EnvFilter::new("info"))))
    //     .with(otel_layer)
    //     .init();

    // Set up database connection
    let db_uri = "sqlite:../db.sqlite?mode=rwc";
    log::info!("Connecting to database on {db_uri}"); // Task 1.1
    // log::info!(db_uri; "Connecting to database"); // Task 4.2

    let db = Database::connect(db_uri)
        .await
        .expect("Failed to connect to the database");

    // Migrate database schemas
    log::info!("Migrating database schemas"); // Task 1.1 & 4.2
    db.get_schema_registry("craftmine-authentication-service::entities::*")
        .sync(&db)
        .await
        .expect("Failed to migrate the database");
    log::info!("Database schema migration complete"); // Task 1.1 & 4.2

    let db_state = db.clone();

    // Start the HTTP server
    let default_port: u16 = 65432;
    let port = var("PORT")
        .unwrap_or(default_port.to_string())
        .parse::<u16>()
        .unwrap_or(default_port);

    log::info!("Starting HTTP server on port {port}"); // Task 1.1
    // log::info!(port; "Starting HTTP server"); // Task 4.2
    HttpServer::new(move || {
        App::new()
            .app_data(web::Data::new(db_state.clone()))
            .service(endpoints::healthz::healthz)
            .service(endpoints::player::create)
            .service(endpoints::player::auth)
            .service(
                web::scope("")
                    .wrap(from_fn(authenticated))
                    .service(endpoints::player::change_name)
                    .service(endpoints::player::change_password)
                    .service(endpoints::player::get_me)
                    .service(endpoints::player::get_player),
            )
    })
    .bind(("0.0.0.0", port))?
    .run()
    .await?;

    // Cleanup resources
    log::info!("Shutting down, closing database connection"); // Task 1.1 & 4.2
    db.close()
        .await
        .expect("Failed to close database connection");

    // Task 4.1
    // logger_provider.shutdown().unwrap();

    Ok(())
}
