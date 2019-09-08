const path = require('path');
const DIST_DIR = path.resolve(__dirname, "dist");
const SRC_DIR = path.resolve(__dirname, "src");
const HtmlWebpackPlugin = require('html-webpack-plugin');
const { CleanWebpackPlugin } = require('clean-webpack-plugin');
const MiniCssExtractPlugin = require("mini-css-extract-plugin");

module.exports = {
	entry: {
		main: SRC_DIR + "/index.bs.js"
	},
	output: {
		filename: '[name].js',
		path: DIST_DIR,
		publicPath: '/'
	},
	module: {
    rules: [
			{
        test: /\.css$/,
        use: [
          MiniCssExtractPlugin.loader,
          "css-loader", "postcss-loader",
          ],
      },
      {
        test: /\.(js|jsx)$/,
        exclude: /node_modules/,
        use: {
          loader: "babel-loader"
        }
			}
    ]
  },
	plugins: [
		new MiniCssExtractPlugin({
      filename: "styles.css",
      chunkFilename: "styles.css"
    }),
		new HtmlWebpackPlugin({
			template: 'index.html'
		}),
		new CleanWebpackPlugin()
	]
}