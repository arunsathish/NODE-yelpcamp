var express     = require("express");
var router      = express.Router();
var passport    = require("passport");
var User        = require("../models/user");

router.get("/", function(req, res){
    res.render("landing");
});

router.get("/register", function(req, res){
    res.render("register");
});

router.post("/register", function(req, res){
    var newUser = new User({username: req.body.username});
    User.register(newUser, req.body.password, function(err, user){
        if(err) {
            req.flash("error", err.message );
            return res.redirect("/register");
        }
        var auth = passport.authenticate("local");
        auth(req, res, function(){
            req.flash("success", "Welcome to YelpCamp" + user.username);
            res.redirect("/campground");
        });
    });
});

router.get("/login", function(req, res){
    res.render("login");
});

var middleware = passport.authenticate("local", { successRedirect: "/campground", failureRedirect: "/login"});
router.post("/login", middleware, function(req, res){});


router.get("/logout", function(req, res){
    req.logout();
    req.flash("success", "Logged you out");
    res.redirect("/campground");
});

module.exports = router;