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
  $NEWTYPE=filter_input(INPUT_POST,'NEWTYPE');

  $query1 = "UPDATE FINAL_PRODUCTS
             SET TYPE = '$NEWTYPE'
             WHERE FINAL_PRODUCTS.SKU = '$SKU'";

  if($query1==NULL){
         echo "No record available.";
   }

   else{

                if($conn->query($query1)){
                  echo "Updated successfully";
                }
                else{
                  echo "Error: ". $query1."
                  ".$conn->error;
                }

     }
   }

   $conn = null;


?>

</br><button class="button"><a href = "home.php">Home </a></button>
