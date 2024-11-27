extends Node2D

signal reset
signal increment_score

onready var collected_coins: Array = []

func _reset_scene():
	print("reset scene")
	collected_coins = []
	emit_signal("reset")
	
	
func _increment_score(coin_id):
	if coin_id in collected_coins:
		print("Already collected")
	else:
		emit_signal("increment_score")
		collected_coins.push_back(coin_id)
		print(coin_id)
		var coin = instance_from_id(coin_id)
		
		coin.collected()
	

# Called when the node enters the scene tree for the first time.
func _ready():
	var player = get_node("Player")
	
	player.connect("health_depleted", self, "_reset_scene")
	player.connect("coin_collected", self, "_increment_score")


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
