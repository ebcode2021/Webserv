<?php
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        // 파일이 업로드되었는지 확인
        if (isset($_FILES["fileToUpload"])) {
            $file = $_FILES["fileToUpload"];

            // 업로드된 파일의 정보
            $fileName = $file["name"];
            $fileType = $file["type"];
            $fileSize = $file["size"];
            $fileTmpPath = $file["tmp_name"];
            $fileError = $file["error"];

            // 파일을 저장할 디렉토리
            $uploadDir = "uploads/";

            // 파일을 새로운 경로로 이동
            $targetPath = $uploadDir . $fileName;
            move_uploaded_file($fileTmpPath, $targetPath);

            echo "파일 업로드 성공!<br>";
            echo "파일 이름: " . $fileName . "<br>";
            echo "파일 타입: " . $fileType . "<br>";
            echo "파일 크기: " . $fileSize . " 바이트<br>";
            echo "임시 파일 경로: " . $fileTmpPath . "<br>";
        } else {
            echo "파일을 선택해주세요.";
        }
    }
?>
