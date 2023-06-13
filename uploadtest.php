<?php
// 업로드된 파일 정보 확인
$uploadedFile = $_FILES['file'];

echo "file = ";

echo "$uploadedFile";

// 업로드된 파일의 임시 경로
$tempFilePath = $uploadedFile['tmp_name'];

// 업로드된 파일의 원본 이름
$originalFileName = $uploadedFile['name'];

// 저장할 파일 경로
$destinationPath = '/Users/minsu/Desktop/42seoul/webserv/resources' . $originalFileName;

// 파일을 원하는 경로로 이동
if (move_uploaded_file($tempFilePath, $destinationPath)) {
    echo '파일이 성공적으로 업로드되었습니다.';
} else {
    echo '파일 업로드에 실패했습니다.';
}
?>