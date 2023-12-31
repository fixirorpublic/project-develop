//import modules npm
const express = require('express');
const bodyParser = require('body-parser')
require('dotenv').config()

//import components
const whatsappRoutes = require("./routes/wa")
const userRoutes = require('./routes/users')
const middlewareLogRequest = require('./middleware/logs')

const app = express()
const port = process.env.PORT || 5000;

app.use(express.urlencoded({extended: true}));
app.use(bodyParser.json());

app.use(middlewareLogRequest);

app.use("/api", whatsappRoutes);
app.use('/users', userRoutes);

app.listen(port, () => {
  console.log(`Server running on port ${port}`)
})