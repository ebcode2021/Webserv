<?php
// 표준 입력에서 데이터를 읽어옴
$input = file_get_contents('php://input');

sleep(1);

$inputlength = strlen($input);
echo "input length = ";
echo $inputlength;
echo "\n";



// Content-Type 헤더에서 boundary 값을 추출
preg_match('/boundary=(.*)$/', $_SERVER['CONTENT_TYPE'], $matches);
$boundary = $matches[1];

echo $input;

// 데이터를 boundary를 기준으로 분할
$parts = explode("--$boundary", $input);
$parts = array_map('trim', $parts);
$parts = array_filter($parts);

echo "boundary = ";
echo $boundary;
echo "\n";
echo $parts[0];

// 분할된 파트를 처리
// list($header, $body) = explode("\r\n\r\n", $part, 2);

// // 파트의 헤더를 배열로 변환
// $headerLines = explode("\r\n", $header);
// $headers = array();
// foreach ($headerLines as $line) {
//     list($key, $value) = explode(': ', $line);
//     $headers[$key] = $value;
// }
// foreach ($parts as $part) {
//     // 파트의 헤더와 본문을 분리
//     echo "a";
//     // 파일인지 확인
//     if (isset($headers['Content-Disposition']) && strpos($headers['Content-Disposition'], 'filename=') !== false) {
//         // 파일 이름 추출
//         preg_match('/filename="(.*)"/', $headers['Content-Disposition'], $matches);
//         $filename = $matches[1];
//         echo $filename;

//         // 파일을 저장할 경로 지정
//         $uploadPath = '/Users/minsu/Desktop/42seoul/webserv/resources/' . $filename;

//         // 파일을 업로드
//         file_put_contents($uploadPath, $body);
//     }
// }

list($header, $body) = explode("\r\n\r\n", $parts[0], 2);

echo $header;
// 헤더를 배열로 변환
$headerLines = explode("\r\n", $header);
$headers = array();
foreach ($headerLines as $line) {
    list($key, $value) = explode(': ', $line);
    $headers[$key] = $value;
}

echo "B";

// 파일인지 확인
if (isset($headers['Content-Disposition']) && strpos($headers['Content-Disposition'], 'filename=') !== false) {
    // 파일 이름 추출
    preg_match('/filename="(.*)"/', $headers['Content-Disposition'], $matches);
    $filename = $matches[1];
    echo $filename;

    // 파일을 저장할 경로 지정
    $uploadPath = '/Users/minsu/Desktop/42seoul/webserv/resources/' . $filename;

    // 파일을 업로드
    file_put_contents($uploadPath, $body);
    echo "C";
}
echo "종료";

?>