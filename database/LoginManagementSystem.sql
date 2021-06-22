use LoginManagementSystem;

create table users(
	user_id INT,
    user_full_name VARCHAR(60),
    user_country VARCHAR(60),
    user_phone VARCHAR(40),
    user_email VARCHAR(30),
    username VARCHAR(30),
    user_password VARCHAR(30),
    
    PRIMARY KEY(user_id)
);
