var express = require('express');
var bodyParser = require('body-parser');

app = express();

app.use(bodyParser.urlencoded({extended: true}));
app.use(bodyParser.json());
app.use(express.static(__dirname + '/public'));
app.set('view engine', 'ejs');

var data = {
    tmp: 0, hmd: 0
}

app.get('/', (req, res) => {
    res.end(JSON.stringify(data));
});

app.post('/', (req, res) => {
    var tmp = req.body.tmp;
    var hmd = req.body.hmd;
    data.tmp = tmp;
    data.hmd = hmd;
    res.end('ok');
});

app.get('/app', (req, res) => {
    res.render('index', {tmp: data.tmp, hmd: data.hmd});
});

app.listen(1337);