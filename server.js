const express = require('express');
const path = require('path');

const port = process.env.PORT || 8000;
const app = express();
const publicPath = __dirname + '/dist';
app.use(express.static(publicPath));

app.get('*', (req, res) => {
	res.sendFile(path.resolve(publicPath, 'index.html'));
})

app.listen(port, () => {
  console.log(`started on port ${port}`);
});