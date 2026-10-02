import React, { useEffect, useState } from 'react';
import ImageCard from './ImageCard';

const ImageSearch = () => {
  const [text, setText] = useState('');
  const [images, setImage] = useState([]);
  const onSubmit = async e => {
    let path;
    if (text == '') {
      path = '/photos';
    } else {
      path = `/photos/search?q=${encodeURI(text)}`;
    }

    const response = await fetch(`${process.env.REACT_APP_API_BASE_URL}${path}`, {
      method: 'GET'
    });
    setImage(await response.json());
  };

  useEffect(() => {
    void onSubmit();
  }, []);

  return (
    <div className="flex flex-col items-center">
      <div
        className="max-w-sm rounded
        overflow-hidden
        my-10 mx-auto"
      >
        <div
          className="flex items-center
            border-b
            border-b-2
            border-green-800 py-2"
        >
          <input
            onChange={e => setText(e.target.value)}
            value={text}
            className="appearance-none bg-transparent border-none
            w-full
            text-green-800 mr-3 py-1 px-2 leading-tight focus:outline-none"
            type="text"
            placeholder="Finde dein Bild..."
          />
          <button
            className="flex-shrink-0
            bg-green-800
            hover:border-teal-700
            text-sm
            border-4
            text-white
            py-1 px-2
            rounded"
            onClick={onSubmit}
          >
            Suchen
          </button>
        </div>
      </div>

      <div className="flex flex-wrap justify-center gap-2 overflow-auto">
        {images.map(image => (
          <ImageCard image={image.imageUrl} name={image.name} />
        ))}
      </div>
    </div>
  );
};
export default ImageSearch;
