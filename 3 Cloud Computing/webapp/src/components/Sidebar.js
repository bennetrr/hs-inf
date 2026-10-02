import React from 'react';
import { Link } from 'react-router-dom';

const Sidebar = () => {
  const handleLogout = () => {
    console.log('Logged out');
  };

  return (
    <div className="fixed h-screen bg-green-500 w-64 p-4 text-white flex flex-col">
      <h1 className="text-2xl font-bold mb-8">Meine App</h1>

      {/* Navigation links */}
      <ul className="flex-grow">
        <li className="mb-4">
          <Link to="/" className="hover:text-gray-200">
            Home
          </Link>
        </li>
        <li className="mb-4">
          <Link to="/about" className="hover:text-gray-200">
            About
          </Link>
        </li>
        <li className="mb-4">
          <Link to="/login" className="hover:text-gray-200">
            Login
          </Link>
        </li>
      </ul>

      <button
        onClick={handleLogout}
        className="mt-auto w-full bg-red-500 hover:bg-red-600 text-white py-2 rounded-full"
      >
        Logout
      </button>
    </div>
  );
};

export default Sidebar;
