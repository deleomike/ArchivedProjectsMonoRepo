extends Control


const HEART_PIXEL_SPACE = 15

var hearts = 4 setget set_hearts
var max_hearts = 4 setget set_max_hearts

onready var heartUIFull = $HeartsFull
onready var heartUIEmpty = $HeartsEmpty


func set_heart_ui_full():
	if heartUIFull != null:
		var x =  hearts * HEART_PIXEL_SPACE
		heartUIFull.rect_size.x = x


func set_heart_ui_empty():
	if heartUIEmpty != null:
		heartUIEmpty.rect_size.x = max_hearts * HEART_PIXEL_SPACE


func set_hearts(value):
	hearts = clamp(value, 0, max_hearts)
	set_heart_ui_full()


func set_max_hearts(value):
	max_hearts = max(value, 1)
	self.hearts = min(hearts, max_hearts)
	set_heart_ui_empty()


func _ready():
	self.max_hearts = PlayerStats.max_health
	self.hearts = PlayerStats.health

	PlayerStats.connect("health_changed", self, "set_hearts")

