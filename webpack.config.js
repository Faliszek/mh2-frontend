const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");

module.exports = {
  mode: "development",
  entry: "./src/index.bs.js",
  plugins: [
    new HtmlWebpackPlugin({
      template: "public/index.html"
    })
  ],
  stats: "errors-only",
  output: {
    filename: "main.js",
    path: path.resolve(__dirname, "dist")
  },
  devServer: {
    contentBase: "./dist",
    hot: true,
    quiet: true
  }
};
