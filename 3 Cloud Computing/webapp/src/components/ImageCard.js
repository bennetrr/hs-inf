import React from 'react';

const ImageCard = ({ image, name }) => {
  return (
    <div className="max-w-sm rounded overflow-hidden shadow-lg">
      <img src={image} alt="" className="w-full" />
      <div className="px-6 py-4">
        <div className="font-bold text-green-600 text-xl mb-2">{name}</div>
      </div>
    </div>
  );
};

export default ImageCard;
