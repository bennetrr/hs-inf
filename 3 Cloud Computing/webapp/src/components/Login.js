import React, { useState } from 'react';

function Login() {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [error, setError] = useState('');

  const handleSubmit = e => {
    e.preventDefault();

    if (email === 'test@test.com' && password === 'password') {
      alert('Erfolgreich eingeloggt!');
      setError('');
    } else {
      setError('Falsche E-Mail oder Passwort');
    }
  };

  return (
    <div className="container mx-auto p-6">
      <h1 className="text-4xl font-bold mb-4">Login</h1>
      {error && <p className="text-red-500 mb-4">{error}</p>}
      <form onSubmit={handleSubmit}>
        <div className="mb-4">
          <label className="block text-lg mb-2" htmlFor="username">
            UserName
          </label>
          <input
            type="email"
            id="email"
            className="w-full p-3 border border-gray-300 rounded-lg"
            value={email}
            onChange={e => setEmail(e.target.value)}
            placeholder="E-Mail eingeben"
            required
          />
        </div>
        <div className="mb-4">
          <label className="block text-lg mb-2" htmlFor="password">
            Passwort
          </label>
          <input
            type="password"
            id="password"
            className="w-full p-3 border border-gray-300 rounded-lg"
            value={password}
            onChange={e => setPassword(e.target.value)}
            placeholder="Passwort eingeben"
            required
          />
        </div>
        <button type="submit" className="w-full bg-green-800 text-white p-3 rounded-lg hover:bg-blue-600">
          Anmelden
        </button>
      </form>
    </div>
  );
}

export default Login;
