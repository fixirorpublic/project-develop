const express = require("express");
const api = require("../controllers/waController")
const router = express.Router();

router.get("/", api);
router.post("/", api);

module.exports = router