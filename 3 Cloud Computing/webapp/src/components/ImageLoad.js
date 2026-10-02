import React, { useState } from 'react';
import { useAuth } from '@clerk/clerk-react';

const ImageLoad = () => {
  const { getToken } = useAuth();
  const [image, setImage] = useState(null);
  const [imageUrl, setImageUrl] = useState('');
  const [name, setName] = useState('');
  const [uploadIndicator, setUploadIndicator] = useState(false);

  const handleImageUpload = event => {
    const file = event.target.files[0];

    if (file) {
      const fileUrl = URL.createObjectURL(file);
      setImageUrl(fileUrl);
      setImage(file);
    }
  };

  const handleSubmit = async () => {
    const formData = new FormData();
    formData.append('image', image);

    formData.append('name', name);

    fetch(`${process.env.REACT_APP_API_BASE_URL}/photos`, {
      method: 'POST',
      body: formData,
      headers: { Authorization: `Bearer ${await getToken()}` }
    })
      .then(response => response.json())
      .then(data => {
        console.log('Bild erfolgreich hochgeladen', data);
        setUploadIndicator(true);
        setTimeout(() => setUploadIndicator(false), 5000);
      })
      .catch(error => {
        console.error('Fehler beim Hochladen des Bildes', error);
      });
  };

  return (
    <div className="container mx-auto p-4">
      <h1 className="text-3xl text-center mb-4">Bild hochladen</h1>

      <input type="file" accept="image/*" onChange={handleImageUpload} className="mb-4 p-2 border rounded" />

      <input
        type="text"
        placeholder="Bild benenen"
        value={name}
        onChange={e => setName(e.target.value)}
        className="mb-4 p-2 border rounded w-full"
      />

      {}
      {imageUrl && (
        <div className="mt-4 text-center">
          <h2 className="text-xl">Vorschau:</h2>
          <img src={imageUrl} alt="Uploaded" className="max-w-xs mt-2" />
        </div>
      )}

      {}
      <button onClick={handleSubmit} className="bg-green-500 text-white px-4 py-2 rounded mt-4">
        Bild hochladen
      </button>

      {uploadIndicator ? <span>Upload erfolgreich</span> : null}
    </div>
  );
};

export default ImageLoad;
