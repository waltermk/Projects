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

  $SKU=filter_input(INPUT_POST,'SKU');
  $query1 = "SELECT FINAL_PRODUCTS.SKU, FINAL_PRODUCTS.Type, FINAL_PRODUCTS.PRODUCT_NO, FINAL_PRODUCTS.RE_NAME
             FROM FINAL_PRODUCTS
             WHERE FINAL_PRODUCTS.SKU='$SKU'";
  {

  if($query1==null){
    echo "No Record Available";
    die();
  }
  else{
    $stmt = $conn->prepare($query1);
    $stmt->execute(array(':SKU'=>$SKU));
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
    echo "SKU        : "; echo $row["SKU"]; echo '</br>';
    echo "Type       : "; echo $row["Type"]; echo '</br>';
    echo "Product No : "; echo $row["PRODUCT_NO"]; echo '</br>';
    echo "Repurpose Center : "; echo $row["RE_NAME"]; echo '</br>';
  }
  ?>
  <button class="button"><a href = "home.php">Home </a></button>
 </body>
 </html>
