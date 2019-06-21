let sendMessage = (_call, request, callback) => {
  Js.log(request);

  let file =
    Node.Fs.readFileSync("/Users/jakubdarul/tmp/ola.pdf",`binary) -> Node.Buffer.fromStringWithEncoding(`binary);

  let response = Grpc.Pdfservice.PdfResponse.make(~pdf=file,());

  Grpc.reply(callback, response);
};

let errorHandler = str => {
  Js.log(str);
  Grpc.Pdfservice.PdfResponse.make();
};

let pdfService =
  Grpc.Pdfservice.PdfService.make(
    ~getPdf=sendMessage,
    ~getPdfErrorHandler=errorHandler,
  );

let credentials = Grpc.Server.Credentials.Insecure.make();

let server = Grpc.Server.make("127.0.0.1:12345", ~credentials, ~pdfService);
