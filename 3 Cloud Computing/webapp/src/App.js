import React, { useState, useEffect } from 'react';
import { BrowserRouter as Router, Routes, Route, Link } from 'react-router-dom';
import ImageCard from './components/ImageCard';
import ImageSearch from './components/ImageSearch';
import About from './components/About';
import Login from './components/Login';
import Sidebar from './components/Sidebar';
import LoadPage from './components/ImageLoad';
import { Protect, SignedIn, SignedOut, SignInButton, UserButton } from '@clerk/clerk-react';

function App() {
  return (
    <Router>
      <div className="flex h-screen">
        <div className="w-1/7 bg-green-800 text-white flex flex-col">
          <h2 className="text-3xl font-bold p-4">CloudyPic</h2>
          <nav className="flex flex-col px-4">
            <Link to="/" className="py-2 text-lg hover:bg-gray-400 rounded">
              Home
            </Link>
            <Link to="/about" className="py-2 text-lg hover:bg-gray-400 rounded">
              About
            </Link>
            <Link to="/load" className="py-2 text-lg hover:bg-gray-400 rounded">
              Load
            </Link>
            <SignedOut>
              <SignInButton />
            </SignedOut>
            <SignedIn>
              <UserButton />
            </SignedIn>
          </nav>
        </div>

        <div className="flex-1 container mx-auto">
          <Routes>
            <Route path="/" element={<ImageSearch />} />
            <Route path="/about" element={<About />} />
            <Route path="/login" element={<Login />} />
            <Route
              path="/load"
              element={
                <Protect>
                  <LoadPage />
                </Protect>
              }
            />
          </Routes>
        </div>
      </div>
    </Router>
  );
}

export default App;
