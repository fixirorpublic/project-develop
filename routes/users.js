const express = require("express")
const userController = require('../controllers/userController')

const router = express.Router()

router.post('/', userController.createNewUsers);

router.get('/', userController.getAllUsers);

router.patch('/', userController.updateUsers);

router.delete('/', userController.deleteUsers);


module.exports = router;