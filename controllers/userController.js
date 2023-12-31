const UserModels = require('../models/usersModels')

const getAllUsers = async(req, res) => {
    try{
        const [data] = await UserModels.getAllUsers();
        res.json({
            message : "Get All Users Success",
            data: data
        })
    } catch (error) {
        res.status(500).json({
            message: 'Server Error',
            serverMessage: error
        })
    }
}

const createNewUsers = (req, res) => {
    res.json({
        message : "Post All Users Success"
    })
}

const updateUsers = (req, res) => {
    res.json({
        message : "Update All Users Success"
    })
}

const deleteUsers = (req, res) => {
    res.json({
        message : "Delete All Users Success"
    })
}

module.exports = {
    getAllUsers,
    createNewUsers,
    updateUsers,
    deleteUsers
}