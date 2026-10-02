const express = require('express');
const app = express();
const AWS = require('aws-sdk');

// AWS S3
const s3 = new AWS.S3({
  accessKeyId: process.env.AWS_ACCESS_KEY_ID,
  secretAccessKey: process.env.AWS_SECRET_ACCESS_KEY,
  region: 'us-east-1'
});

app.get('/images', (req, res) => {
  const params = {
    Bucket: 'your-s3-bucket-name',
    Prefix: 'images/'
  };

  s3.listObjectsV2(params, (err, data) => {
    if (err) {
      return res.status(500).json({ error: err.message });
    }
    const imageUrls = data.Contents.map(item => `https://${params.Bucket}.s3.amazonaws.com/${item.Key}`);
    res.json(imageUrls);
  });
});

app.listen(5000, () => console.log('Server is running on port 5000'));
