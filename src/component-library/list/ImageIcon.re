open Icon;

module ImageIcon =
  Make({
    [@bs.module  "@material-ui/icons/Person"]
    external reactClass: React.component('a) = "default";
  });
