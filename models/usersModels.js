const pool = require('../config/database')

const getAllUsers = () => {
    const SQLQuery = 'SELECT * FROM users'

    return pool.execute(SQLQuery);
}

module.exports = {
    getAllUsers,
}