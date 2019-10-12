import React from "react";

export function Welcome(props) {
  return <div>
      <h1>Hello, {props.name}</h1>
      <h1>Hello, {props.age ? props.age : 34}</h1>
  </div>;
}