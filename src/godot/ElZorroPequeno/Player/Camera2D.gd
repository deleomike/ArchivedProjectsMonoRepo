extends Camera2D


onready var topLeft = $Limits/UpperLeft
onready var bottomRight = $Limits/BottomRight


func _ready():
	limit_top = topLeft.global_position.y
	limit_left = topLeft.global_position.x
	limit_right = bottomRight.global_position.x
	limit_bottom = bottomRight.global_position.y

