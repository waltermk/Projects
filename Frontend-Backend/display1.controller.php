<?php

$host="localhost";
$dbusername="root";
$dbpassword="";
$dbname="FOHOR_MALAI";

$conn=new PDO('mysql:host='.$host.';dbname='.$dbname,$dbusername,$dbpassword);

if(mysqli_connect_error())
{
  die('Connect Error ('. mysqli_connect_errorno().')'
  .mysqli_connect_error());
}

else {

  $PNO=filter_input(INPUT_POST,'PNO');
  $query1 = "SELECT PRODUCT_INFO.SKUID, PRODUCT_INFO.TYPE
             FROM PRODUCT_INFO
             WHERE PRODUCT_INFO.NO = '$PNO'";

  {

  if($query1==null){
    echo "No Record Available";
    die();
  }
  else{
    $stmt = $conn->prepare($query1);
    $stmt->execute(array(':PNO'=>$PNO));
    $rows= $stmt->fetchALL(PDO::FETCH_ASSOC);
  }
}
}

$conn = null;
?>

<!DOCTYPE html>
<html lang = "en">
<head>
</head>
<body>

<?php
foreach($rows as $row){

    echo "SKU     : "; echo $row["SKUID"]; echo '</br>';
    echo "Type    : "; echo $row["TYPE"]; echo '</br>';
  }
  ?>
  <button class="button"><a href = "home.php">Home </a></button>
 </body>
 </html>
