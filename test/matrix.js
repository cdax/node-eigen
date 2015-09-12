var eigen = require('../build/Release/eigen');

var matrix = new eigen.Matrix(5, 5);

console.log(matrix.rows(), matrix.cols(), matrix.size());
