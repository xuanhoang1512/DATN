var mysql = require("mysql");
var express = require("express"),
    app = express();
app.use('/', express.static(__dirname ));
app.get('/',function(req, res){
    res.sendfile(__dirname + '/web.html');
});
var server = require("http").createServer(app).listen(5000, function(){
    console.log("Server Running.....\nListening : localhost:5000");
});
var io = require("socket.io").listen(server);
var data_mysql = {
    table: "datas"
};
var db = mysql.createConnection({
    host: "localhost",
    port: 3306,
    user: "root",
    password: "1",
    dateStrings: true,
    database: "datn"
});
function mysql_connect(){
    db.connect(function (err) {
        if(err)
            throw(err);
        console.log("Connected MySQL");
    });
}
function mysql_query(sql, callback){
    db.query(sql, function(err, result, fields){
        if(err)
            throw err;
        return callback(result);
    });
}
function mysql_close(){
    db.end();
    console.log("Disconnected MySQL");
}
mysql_connect();
setInterval(function () {
    mysql_query("SELECT * FROM " + data_mysql.table + " ORDER BY STT DESC LIMIT 15", function(callback){
		io.sockets.emit("data", JSON.stringify(callback));         
    });
}, 1000);