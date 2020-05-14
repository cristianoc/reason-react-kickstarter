type t('result) =
|  Loading(option('result))
|  Live('result)
|  Error(Decco.decodeError)
 