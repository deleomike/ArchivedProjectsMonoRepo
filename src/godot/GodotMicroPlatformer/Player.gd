extends KinematicBody2D


var speed: int = 200
var jump_force: int = 900
var gravity: int = 3000

var velocity: Vector2 = Vector2()

var sprite_idle = load("res://Sprites/Player_Idle.png")

var sprite_jump = load("res://Sprites/Player_Jump.png")

var sprite_walk_animations: Array = [
	load("res://Sprites/Player_Walk1.png"),
	load("res://Sprites/Player_Walk2.png")
]
var sprite_walk_animation_state: int = 0
var sprite_walk_animation_duration: float = 0.2
var sprite_walk_duration_count: float = sprite_walk_animation_duration

onready var sprite: Sprite = get_node("Sprite") # reference to player sprite node


signal health_depleted
signal coin_collected(coin_id)


func reset_player():
	emit_signal("health_depleted")
	
	position = Vector2(140, 0)
	

func collect_coin(coin_id):
	emit_signal("coin_collected", coin_id)


func increment_sprite_walk_index(delta):
	if sprite_walk_duration_count < 0:
		sprite_walk_animation_state += 1
		sprite_walk_duration_count = sprite_walk_animation_duration
	else:
		sprite_walk_duration_count -= delta
	# reset
	if len(sprite_walk_animations) == sprite_walk_animation_state:
		sprite_walk_animation_state = 0


func _physics_process(delta):
	"""
	If we press the right or left, this applies the physics
	
	This is called 60 times per minute
	delta: distance or time duration between each frame (1/60)
	"""
	
	velocity.x = 0
	
	# movement inputs
	if Input.is_action_pressed("move_left"):
		velocity.x -= speed
	elif Input.is_action_pressed("move_right"):
		velocity.x += speed
		
	# applying the movements
	velocity = move_and_slide(velocity, Vector2.UP)
	
	# gravity
	velocity.y += gravity * delta
	
	if Input.is_action_just_pressed("jump") and is_on_floor():
		# is_on_floor is a built in function for whether we are standing on the ground
		velocity.y -= jump_force
		
	
	# Sprint Movements
	if velocity.y < 0:
		# jump
		sprite.texture = sprite_jump
	elif velocity.x != 0:
		# walk
		sprite.texture = sprite_walk_animations[sprite_walk_animation_state]
		increment_sprite_walk_index(delta)
	else:
		#idle
		sprite.texture = sprite_idle
		
	
	# sprite direction
	if velocity.x < 0:
		sprite.flip_h = true
	elif velocity.x >= 0:
		sprite.flip_h = false
		
	for i in get_slide_count():
		var collision = get_slide_collision(i)
		if collision.collider.is_in_group("Enemy"):
			reset_player()
			print("Enemy collision")
		elif collision.collider.is_in_group("Coin"):
			collect_coin(collision.collider_id)
		#print("Collided with: ", collision.collider.name)
		
	


