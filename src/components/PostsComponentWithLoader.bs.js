// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Network$ReactTemplate = require("../repo/Network.bs.js");
var LoaderComponent$ReactTemplate = require("../componentLibrary/loader-component/LoaderComponent.bs.js");

function PostsComponentWithLoader$PostsViewComponent(Props) {
  var posts = Props.posts;
  var refeshView = Props.refeshView;
  return React.createElement("div", undefined, React.createElement("li", undefined, $$Array.of_list(List.map((function (post) {
                            return React.createElement("ul", {
                                        key: String(post[/* id */0])
                                      }, React.createElement("h1", undefined, post[/* title */1]));
                          }), posts))), React.createElement("button", {
                  onClick: (function (_event) {
                      return Curry._1(refeshView, /* () */0);
                    })
                }, "Refresh"));
}

var PostsViewComponent = /* module */[/* make */PostsComponentWithLoader$PostsViewComponent];

var LoaderComponentConfig = /* module */[];

var PostsLoaderComponent = LoaderComponent$ReactTemplate.LoaderComponent(LoaderComponentConfig);

function PostsComponentWithLoader$PostsComponentWithLoader(Props) {
  return React.createElement(PostsLoaderComponent[/* make */0], {
              fetchData: (function (param) {
                  return Network$ReactTemplate.fetchPosts(/* () */0);
                }),
              renderView: (function (posts, refeshView) {
                  return React.createElement(PostsComponentWithLoader$PostsViewComponent, {
                              posts: posts,
                              refeshView: refeshView
                            });
                })
            });
}

var PostsComponentWithLoader = /* module */[
  /* LoaderComponentConfig */LoaderComponentConfig,
  /* PostsLoaderComponent */PostsLoaderComponent,
  /* make */PostsComponentWithLoader$PostsComponentWithLoader
];

exports.PostsViewComponent = PostsViewComponent;
exports.PostsComponentWithLoader = PostsComponentWithLoader;
/* PostsLoaderComponent Not a pure module */