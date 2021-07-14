# Alloy Engine
2D engine data oriented in c++

## Exemples

### Planets
Planets and asteroids rotating around a star

### Water simulation
Proceduraly generated 2D level using cellular automata. Updating water that fall and equalize itself with its surounding. Two lights are also present in the scene.

## Versions

### V 0.3
- New project "Planets"
- Add RandomRange to math
- Graphics primitive to be drawn as plain object without texture
- New Component Renderer2D, it needs a position and a scale to be drawn correctly
- TilemapeManager contains multiples tilemaps

### V 0.2
- Core Engine 
	- Refactor Service Locator
- ECS
	- Implement basics Entity / Component / System
	- Possibility to read/write one entity
- Separate exemples from engine into their own projects

### V 0.1
- Core Engine 
	- Service Locator to hold every main manager
	- Update loop 
		- Init
		- Update (not deterministic)
	- Input system (only keyboard)
- Graphics Engine 
	- Windows handling
	- Sprites
	- Tilemap
	- Lights
		- Ambiant 
		- Point Light
- Exemple
	- New water simulation 
- Externals librairies
	- GoogleTest
	- Google Benchmark
	- SFML
	- Remotery
