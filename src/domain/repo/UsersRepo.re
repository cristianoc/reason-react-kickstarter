let dummy_response = [%bs.raw
  {|
    [{
      id: 2, name: "Shubham", src: "https://ca.slack-edge.com/T03CXPZBX-UD8LWV6TT-5e60092ac9d4-512"
    },
    {
    
      id: 3, name: "Tejesh", src: "https://ca.slack-edge.com/T03CXPZBX-U6NLZ6HUH-fbd890599a57-512"
    },
    {
    
      id: 4, name: "Ashutosh", src: "https://ca.slack-edge.com/T03CXPZBX-U6N7UST1S-1ea8555b6704-512"
    },
    {
    
      id: 4, name: "Karan", src: "https://ca.slack-edge.com/T03CXPZBX-UV39NPPL2-1150807fa1f5-512"
    },
    {
    
      id: 4, name: "Dwarika", src: "https://ca.slack-edge.com/T03CXPZBX-UTUSN3073-09cf29b2f5ac-512"
    },
    {
    
      id: 4, name: "Aman", src: "https://ca.slack-edge.com/T03CXPZBX-U0101SFJ8PJ-859f859d0ad0-512"
    }]
  |};
]

module StateMapper = {
  let decodeUser = (json: Js.Json.t) : User.user => {
    Json.Decode.(
      {
        id: json |> field("id", int),
        name: json |> field("name", string),
        src: json |> field("src", string),
      }
    )
  }

  let execute = (json: Js.Json.t) : User.t => {
    json |> Json.Decode.list(decodeUser)
  }
}

let fetchUsers = () : Js.Promise.t(User.t) =>
  Js.Promise.(
    make((~resolve, ~reject as _) =>
        dummy_response
        |> StateMapper.execute
        |> (users) => resolve(. users)
    )
  )