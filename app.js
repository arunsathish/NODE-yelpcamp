var express         = require("express"),
    app             = express(),
    bodyParser      = require("body-parser"),
    mongoose        = require("mongoose"),
    passport        = require("passport"),
    LocalStrategy   = require("passport-local"),
    methodOverride  = require("method-override"),
    flash           = require("connect-flash"),
    Campground      = require("./models/campground"),
    Comment         = require("./models/comment"),
    User            = require("./models/user"),
    seedDB          = require("./seeds");

var campgroundRoute = require("./routes/campgrounds"),
    commentRoute    = require("./routes/comments"),
    indexRoute      = require("./routes/index");

/*
Connecting to Database local Server - MongoDB
    cd C:/Program\ Files/MongoDB/Server/3.6/bin
    mongod --dbpath C:/Users/arun/mongo-data
    
Starting App Server
    node app.js

*/

// mongoose.connect("mongodb://localhost/yelp_camp");
mongoose.connect("mongodb://arun:arunpassword@ds049548.mlab.com:49548/yelpcamp");


app.use(bodyParser.urlencoded({extended: true}));
app.set("view engine", "ejs");
// app.use(express.static("public"));
app.use(express.static(__dirname + "/public"));
app.use(methodOverride("_method"));
app.use(flash());
// seedDB(); // seed the database

//PASSPORT CONFIG
app.use(require("express-session")({
    secret: "Once again Rusty wins cutest dog!, Because for some random text",
    resave: false,
    saveUninitialized: false
}));
app.use(passport.initialize());
app.use(passport.session());
passport.use(new LocalStrategy(User.authenticate()));
passport.serializeUser(User.serializeUser());
passport.deserializeUser(User.deserializeUser());

app.use(function(req, res, next){
    res.locals.currentUser  = req.user;
    res.locals.error        = req.flash("error");
    res.locals.success      = req.flash("success");
    next();
});

app.use("/campground", campgroundRoute);
app.use("/campground/:id/comment", commentRoute);
app.use(indexRoute);


app.listen(process.env.PORT || 3000, function() {
    console.log("Yelp Camp Server has Started");
});