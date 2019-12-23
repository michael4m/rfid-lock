<?php
  
	include 'db_access.php';

	$rfid = $_POST['rfid'];
	$pintu = $_POST['pintu'];	

	$result = mysqli_query($conn,"SELECT * FROM user WHERE kode_rfid='".$rfid."' LIMIT 1");

	if ($result){
		$row = mysqli_fetch_assoc($result); 
		$nama = getValue($row, 'nama');
		$kategori = getValue($row, 'kategori');

		echo "nama : ".$nama." | kategori : ".$kategori;
		  	   
	}
	else{
	    echo "Terjadi Kesalahan.<br>";
	    // echo $waktu;  
	}


	function getValue($baris, $parameter){
      	return $baris[$parameter];  
	}
	
?>