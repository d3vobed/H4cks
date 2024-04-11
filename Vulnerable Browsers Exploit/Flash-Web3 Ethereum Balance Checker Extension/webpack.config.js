const path = require("path");
const CopyWebpackPLugin = require("copy-webpack-plugin")

module.exports = {
    entry: {
        popup: "./src/popup.js",
        serviceWorker: "./src/serviceWorker.js"
    },
    output: {
        filename: '[name].bundle.js',
        path: path.resolve(__dirname, 'dist')
    },
    devtool: 'source-map',
    mode: 'development',
    watch: true,
    plugins: [
        new CopyWebpackPLugin({
            patterns: [{from: 'static'}]
        })
    ]
}
