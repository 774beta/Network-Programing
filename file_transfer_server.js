const fs = require('fs');
const path = require('path');
const WebSocket = require('ws');

const PORT = 50000;
const HOST = '0.0.0.0';
const CHUNK_SIZE = 80;
const END_MESSAGE = 'exit_send';
const STUDENT_ID_PATTERN = /^[A-Za-z0-9]{8}$/;

const server = new WebSocket.Server({ host: HOST, port: PORT }, () => {
  console.log(`File transfer server listening on ws://${HOST}:${PORT}`);
});

function getRequestedFile(studentId) {
  if (!STUDENT_ID_PATTERN.test(studentId)) {
    throw new Error('学籍番号は半角英数字8文字で入力してください。');
  }

  return path.join(__dirname, `${studentId}.txt`);
}

function sendFile(ws, filePath) {
  const text = fs.readFileSync(filePath, 'utf8');

  for (let index = 0; index < text.length; index += CHUNK_SIZE) {
    ws.send(text.slice(index, index + CHUNK_SIZE));
  }

  ws.send(END_MESSAGE);
}

server.on('connection', ws => {
  console.log('client connected');

  ws.on('message', message => {
    const studentId = message.toString('utf8').trim();
    console.log(`request: ${studentId}`);

    try {
      const filePath = getRequestedFile(studentId);
      sendFile(ws, filePath);
      console.log(`sent: ${path.basename(filePath)}`);
    } catch (error) {
      ws.send(`error:${error.message}`);
      ws.send(END_MESSAGE);
      console.error(error.message);
    }
  });

  ws.on('close', () => {
    console.log('client disconnected');
  });
});
