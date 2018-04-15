var middlewareObj   = {};
var Campground      = require("../models/campground");
var Comment         = require("../models/comment");

middlewareObj.checkCampgroundOwnership = function(req, res, next){
    if(req.isAuthenticated()) {
        Campground.findById(req.params.id, function(err, foundCamp){
            if(err){
                req.flash("error", "Campground Not Found");
                res.render("back");
            } else {
                // Check if current user have permission to Edit the campground
                if(foundCamp.author.id.equals(req.user._id)){
                    next();
                } else {
                    req.flash("error", "Permission Denied");
                    res.redirect("back");
                }
                
            }
        });
    } else {
        req.flash("error", "You need to Login First");
        res.redirect("back");
    }
}

middlewareObj.checkCommentOwnership = function(req, res, next){
    if(req.isAuthenticated()) {
        Comment.findById(req.params.comment_id, function(err, foundComment){
            if(err){
                res.render("back");
            } else {
                // Check if current user have permission to Edit the comment
                if(foundComment.author.id.equals(req.user._id)){
                    next();
                } else {
                    req.flash("error", "Permission Denied");
                    res.redirect("back");
                }
                
            }
        });
    } else {
        req.flash("error", "You need to Login First");
        res.redirect("back");
    }
}

middlewareObj.isLoggedIn = function(req, res, next) {
    if(req.isAuthenticated()){
        return next();
    }
    req.flash("error", "Need to Login First");
    res.redirect("/login");
}

module.exports = middlewareObj;