extends Area2D


func _on_HealthDrop_body_entered(_body):
	if !PlayerStats.is_health_full():
		PlayerStats.health += 1
		queue_free()
