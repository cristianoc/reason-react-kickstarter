type t('result) =
|  Loading(option('result))
|  Success('result)
|  Error(Decco.decodeError)
 