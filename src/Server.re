/* Error handler for ChatService.SendMessage RPC */
let sendMessageErrorHandler = error =>
  Grpc.Chat.MessageReply.make(~error, ());

/* Implementation for ChatService.sendMessage RPC */
let sendMessage = (_call, request, callback) => {
  Js.log2("sendMessageRequest=", request);
  Js.log2("urgency=", request->Grpc.Chat.MessageRequest.urgencyGet);
  let (_, text, urgency,bajteczki) =
    Grpc.Chat.MessageRequest.(
      Belt.Option.(
        request->channelGet->getExn,
        request->textGet->getExn,
        request->urgencyGet->getExn,
        request->bajteczkiGet->getExn,
      )
    );

  Js.log4("ChatServer.re got MessageRequest",  text, urgency,bajteczki);

  Grpc.Chat.MessageReply.make(~error="not allowed", ())
  |> Grpc.reply(callback);
};

let chatService =
  Grpc.Chat.ChatService.make(~sendMessage, ~sendMessageErrorHandler);

let credentials = Grpc.Server.Credentials.Insecure.make();

let server = Grpc.Server.make("127.0.0.1:12345", ~credentials, ~chatService);



