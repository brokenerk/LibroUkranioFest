var fs =require("fs")
var text = fs.readFileSync("./10000_formas.txt",'utf8').toString()
var lines = text.split("\n")
console.log(lines)