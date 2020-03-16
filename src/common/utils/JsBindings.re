[@bs.val] [@bs.scope "window"] external redirect: (string, string) => unit = "open";

[@bs.val] [@bs.scope ("window", "history")] external invokeBack: unit => unit = "back";

[@bs.val] [@bs.scope "window"] external scrollTo: (int, int) => unit = "scrollTo";

[@bs.val] [@bs.scope "window"] external encodeURI: string => string = "encodeURI";

[@bs.val] [@bs.scope "document"] external visibilityState: string = "visibilityState";
