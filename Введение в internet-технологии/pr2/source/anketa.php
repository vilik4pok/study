<!DOCTYPE html>
<html lang="ru">
	<head>
		<meta charset="UTF-8">
		<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
		<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.1/dist/js/bootstrap.min.js" integrity="sha384-skAcpIdS7UcVUC05LJ9Dxay8AXcDYfBJqt1CJ85S/CFujBsIzCIv+l9liuYLaMQ/" crossorigin="anonymous"></script>
		<link href="style.css" rel="stylesheet">
	</head>
	<body>
		<nav class="navbar fixed-top navbar-expand-md navbar-dark bg-dark">
			<div class="container-fluid">
				<button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
					<span class="navbar-toggler-icon"></span>
				</button>
				<div class="collapse navbar-collapse" id="navbarSupportedContent">
				   <ul class="navbar-nav me-auto mb-2 mb-lg-0">
						<li class="nav-item"><a class="nav-link" href="index.html">Статья</a></li>
						<li class="nav-item"><a class="nav-link" href="statistic.html">Статистика</a></li>
						<li class="nav-item"><a class="nav-link" href="notes.html">Заметки</a></li>
						<li class="nav-item"><a class="nav-link active" href="anketa.php">Анкета</a></li>
						<li class="nav-item"><a class="nav-link" href="ajax.html">Внешнее API</a></li>
					</ul>
				</div>
			</div>
		</nav>
		<form enctype="multipart/form-data" id="mform" method="post" action="anketa.php">
			<div class="col-10 col-md-7 m-auto">
				<h2 class="text-center">Регистация нового пользователя</h2>
				<div class="row row-cols-1 row-cols-lg-3">
					<div class="col">
						<label>Имя</label>
						<input type="text" name="firstname" class="form-control" id="validationDefault01" placeholder="Имя" pattern="[A-Za-zА-Яа-яЁё]+" required>
					</div>
					<div class="col">
						<label>Фамилия</label>
						<input type="text" name="secondname" class="form-control" id="validationDefault02" placeholder="Фамилия" pattern="[A-Za-zА-Яа-яЁё]+" required>
					</div>
					<div class="col">
						<label>Отчество <small class="form-text text-muted">(Необязательно)</small></label>
						<input type="text" name="thirdname" class="form-control" pattern="[A-Za-zА-Яа-яЁё]+" placeholder="Отчество">
					</div>
					
					<div class="col">
						<label>Email</label>
						<input type="email" name="email" class="form-control" id="inputEmail1" placeholder="Email" required>
					</div>
					<div class="col">
						<label>Пароль</label>
					  <input type="password" name="password" class="form-control" id="inputPassword1" placeholder="Пароль" required>
					</div>
					<div class="col">
						<label>Повторите пароль</label>
						<input type="password" class="form-control" id="inputPassword2" placeholder="Повторите пароль" required>
					</div>

					<div class="col">
						<label>Роль пользователя</label>
						<select id="inputRole" name="role" class="form-control form-select" required>
							<option selected disabled value="">Выберите роль...</option>
							<option>Администратор</option>
							<option>Пользователь</option>
						</select>
					</div>
					<div class="col">
						<label>Репутация пользователя</label>
						<input type="number" name="rate" class="form-control" id="inputRate" placeholder="Репутация пользователя" required>
					</div>
					<div class="col">
						<label>Дата смены пароля</label>
						<input type="date" name="date" class="form-control" id="inputDate" placeholder="Дата смены пароля" required>
					</div>
				
					<div class="col">
						  <label for="form_name">Страна</label>
						  <input name="country" class="form-control" list="datalistOptions" id="exampleDataList" placeholder="Введите название страны" required>
						  <datalist id="datalistOptions">							<option value="Австралия"/><option value="Австрия"/><option value="Азербайджан"/><option value="Албания"/><option value="Аргентина"/><option value="Белоруссия"/>							<option value="Бельгия"/><option value="Болгария"/><option value="Бразилия"/><option value="Великобритания"/><option value="Венгрия"/><option value="Германия"/>							<option value="Греция"/><option value="Грузия"/><option value="Дания"/><option value="Ирландия"/><option value="Исландия"/><option value="Испания"/>							<option value="Италия"/><option value="Казахстан"/><option value="Канада"/><option value="Кипр"/><option value="Китай"/><option value="Латвия"/>							<option value="Литва"/><option value="Мексика"/><option value="Монако"/><option value="Нидерланды"/><option value="Новая Зеландия"/><option value="Норвегия"/>							<option value="Польша"/><option value="Португалия"/><option value="Россия"/><option value="Румыния"/><option value="Сербия"/><option value="Словакия"/>							<option value="Словения"/><option value="Соединенные штаты Америки"/><option value="Таиланд"/><option value="Турция"/><option value="Украина"/><option value="Финляндия"/>							<option value="Франция"/><option value="Хорватия"/><option value="Черногория"/><option value="Чехия"/><option value="Чили"/><option value="Швейцария"/>							<option value="Швеция"/><option value="Эстония"/><option value="Южная корея"/><option value="Япония"/>						  </datalist>
					   </div>
					<div class="col">
						  <label for="form_name">Пол</label>
						  <div class="form-check">
							 <input name="sex" class="form-check-input" type="radio" id="radio1" value="0" checked>
							 <label class="form-check-label">Мужской</label>
						  </div>
						  <div class="form-check">
							 <input name="sex" class="form-check-input" type="radio" id="radio1" value="1">
							 <label class="form-check-label">Женский</label>
						  </div>
				   </div>
				</div>
				
				<div class="row">
					<div class="col-12 col-lg-4">
						<label>Аватар пользователя</label>
						<input type="hidden" name="MAX_FILE_SIZE" value="83886080" />
						<input type="file" name="userfile" class="form-control" id="inputFile" required>
					</div>
				</div>
				
				<div class="row">
					<div class="col-12 col-lg-4">
						<label>Подпись пользователя</label>
						<textarea class="form-control" name="text" id="inputLabelUser" rows="5" required></textarea>
					</div>
				</div>
				
				<div class="row">
					<div class="col">
						<div class="form-check">
							<input name="check" class="form-check-input" type="checkbox" value="ON" id="flexCheckDefault" required>
							<label>Я согласен(-на) с обработкой персональных данных</label>
						</div>
					</div>
				</div>
				
				<div class="row mt-2">
					<div class="col-12 col-lg-4">
						<button type="reset" class="form-control">Очистить</button>
					</div>
					<div class="col-12 col-lg-4">
						<button type="submit" class="form-control">Отправить</button>
					</div>
				</div>
				
				<?php
					if(count($_POST)>0)
					{
						$uploaddir = 'uploads/';
						$uploadfile = $uploaddir.basename('postdata.txt');
						file_put_contents($uploadfile, json_encode(array_merge($_POST, $_FILES)));
						echo "<div class='row mt-2 mb-2'><a href=$uploadfile download>Ссылка на файл</a></div>";
						if ($_FILES['userfile']['error'] == UPLOAD_ERR_OK) {
							if(exif_imagetype($_FILES['userfile']['tmp_name']))
							{						
								$uploadimg = $uploaddir.basename($_FILES['userfile']['name']);
								move_uploaded_file($_FILES['userfile']['tmp_name'], $uploadimg);
								echo "<div class=row-cols-5><img src=$uploadimg></div>";
							}
							else
								echo "<div class=row-cols-5><h5>Загружено не изображение!</h5></div>";
						}
					}
				?>
			
			</div>
		</form>
		<script>
			mform.oninput = function(){
				inputPassword2.setCustomValidity(inputPassword2.value != inputPassword1.value ? (inputPassword2.value == "" ? "Заполните это поле.": "Пароли не совпадают.") : "");
			}
			
		</script>
		<footer class="py-3 my-4">
		  <ul class="nav justify-content-center border-bottom pb-3 mb-3 pt-3 border-top">
			<li class="nav-item"><a href="index.html" class="nav-link px-2 text-muted">Статья</a></li>
			<li class="nav-item"><a href="statistic.html" class="nav-link px-2 text-muted">Статистика</a></li>
			<li class="nav-item"><a href="notes.html" class="nav-link px-2 text-muted">Заметки</a></li>
		  </ul>
		  <p class="text-center text-muted"><a name="footer"></a>©vilik4pok</p>
		</footer>
	</body>
</html>