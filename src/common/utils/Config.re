module Env = {
  [@bs.val] [@bs.scope ("window", "location")] external hostname: string = "hostname";
  [@bs.val] external env: string = "process.env.NODE_ENV";
  [@bs.val] external oms_url: string = "process.env.OMS_URL";
  [@bs.val] external vp_url: string = "process.env.VP_URL";
  [@bs.val] external pdf_generator_lambda_key: string = "process.env.PDF_GENERATOR_LAMBDA_KEY";
  [@bs.val] external pdf_generator_lambda_path: string = "process.env.PDF_GENERATOR_LAMBDA_PATH";
  [@bs.val] external google_maps_api_key: string = "process.env.GOOGLE_MAPS_API_KEY";

  let getHostName = (): string => oms_url;
  let getRnrHostName = (): string => vp_url;
  let getPdfGeneratorUrl = (): string => pdf_generator_lambda_path;
  let getPdfGeneratorLambdaKey = (): string => pdf_generator_lambda_key;
  let getGoogleMapsApiKey = (): string => google_maps_api_key;
};
