import axios from 'axios';

export const api = axios.create({
  baseURL: 'http://localhost:3000',
  headers: {
    'Content-Type': 'application/json'
  }
});

export function setToken(token) {
  api.defaults.headers.Authorization = `Bearer ${token}`;
}

export const clearToken = () => {
  delete api.defaults.headers.Authorization;
};
