<!DOCTYPE html>
<html>
<head>
<title> Fohor Malai </title>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">

<style>

.btn {
  border: 2px solid purple;
  background-color: inherit;
  padding: 15px 30px;
  font-size: 30px;
  cursor: pointer;
  margin: 15px;
  display: inline-block;
  transition: all 0.5s;
  cursor: pointer;
  box-shadow: 0 8px 16px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19);
  border: 2px solid #4CAF50;
  border-radius: 12px;

}

.btn span {
  cursor: pointer;
  display: inline-block;
  position: relative;
  transition: 0.5s;
}


.btn span:after {
  content: '\00bb';
  position: absolute;
  opacity: 0;
  top: 0;
  right: -20px;
  transition: 0.5s;
}

.btn:hover span {
  padding-right: 25px;
}

.btn:hover span:after {
  opacity: 1;
  right: 0;
}

.button_insert, .button_update, .button_display, .button_delete{

  color: blue;
}

.button_insert:hover {
  background-color: lightgreen;

}

.button_display1:hover {
  background-color: lightgreen;

}

.button_display2:hover {
  background-color: lightgreen;

}

.button_display:hover {
  background-color: lightgreen;

}

.button_delete:hover {
  background-color: lightgreen;

}

h1{
  color:green;
  font-size: 50px;
}


body {
  background-image: url('b.jpeg');
  background-repeat: no-repeat;
  background-attachment: fixed;
  background-size: 100% 100%;
}

</style>
</head>
<body>
<div class="container">
  <div class="text-center">
  </br></br></br><img src="fohormalai.jpg" width="500" height="300">

    <h1><b>Fohor Malai: For the envrionment</b></h1>
    <h2><marquee behavior="scroll" direction="right">Sponsered by ECOboost</marquee></h2></br>

      <button class="btn button_insert"><a href = "display.php"><span>Display Final Product</span></a></button>
      <button class="btn button_update"><a href = "update.php"><span>Update SKU</span></a></button>
      <button class="btn button_delete"><a href = "delete.php"><span>Delete</span></a></button></br>
      <button class="btn button_display1"><a href = "display1.php"><span>Table View</span></a></button>
      <button class="btn button_display2"><a href = "display2.php"><span>Table View2</span></a></button>
    </div>
  </div>

</body>
</html>
