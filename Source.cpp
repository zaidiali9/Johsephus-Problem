#include<iostream>
#include<queue>
#include<map>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFMl/Network.hpp>
using namespace std;
using namespace sf;
inline void menu()
{
	cout << "For Instructions Press 1" << endl;
	cout << "Start Game Press 2" << endl;
	cout << "To Quit the Game Press 3" << endl;
}
template<class T>
class Queue {
	class Node {
	public:
		Node()
		{
			next = nullptr;
			//data = 0;
		}
		Node* next;
		T data;
	};
	Node* root;
	Node* end;
public:
	T front()
	{
		return root->data;
	}
	Queue()
	{
		root = nullptr;
		end = nullptr;
	}
	void push(T val)
	{
		if (!root)
		{
			root = new Node;
			root->data = val;
			end = root;
		}
		else
		{
			Node* new_node;
			new_node = new Node;
			new_node->data = val;
			end->next = new_node;
			end = new_node;
			end->next = root;
		}
	}
	T pop()
	{
		if (this->size_queue() == 1)
		{
			Node* temp = root;
			root = nullptr;
			return temp->data;

		}
		Node* temp = root;
		root = root->next;
		end->next = root;
		T data = temp->data;
		delete temp;
		return data;
	}
	void print()
	{
		Node* temp = root;
		do {
			cout << temp->data << " ";
			temp = temp->next;
		} while (temp != root);
	}
	int size_queue()
	{
		int count = 0;
		Node* temp = root;
		do {
			count++;
			temp = temp->next;
		} while (temp != root);
		return count;
	}
};
class Player {
	Texture tex;
	Sprite sprite;
	Vector2f pos;
public:
	Player();
	void render(RenderTarget &target);
	void update(bool flag);
	void setposition(float posx, float posy);
};
class Game {
	SoundBuffer pubg;
	Sound track;
	queue<Player> player_s;
	queue<Player>temp;
	RenderWindow* window;
	VideoMode video_mode;
	int no_players;
	Sprite bAck_gr;
	Texture back;
	CircleShape circle;
	int count;
	bool flag;
	int skips;
public:
	Game(int n,int k);
	void render_back();
	void Run();
	void Update();
	void Render();
	void back_end(int n);
	//void display();
};

Game::Game(int n,int k)
{
	cout<<pubg.loadFromFile("track.wav");
	track.setBuffer(pubg);
	this->skips = k;
	count = 0;
	this->no_players = n;
	video_mode.width = 1920;
	video_mode.height = 1080;
	circle.setRadius(100.f);
	circle.setOutlineThickness(10.f);
	window = new RenderWindow(this->video_mode, "Johsephus Problem", Style::Close | Style::Titlebar | Style::Fullscreen);
	cout<<this->back.loadFromFile("backpro.png");
	this->bAck_gr.setTexture(this->back);
	n = 0;
	Player* obj = new Player[this->no_players];
	float x=100.f, y=150.f;
	float ang = 0;
	double ang2 = (static_cast<double>(360) / this->no_players) * (3.14 / 180);
	while (n != this->no_players)
	{
		x = (350 * cos(ang)) + 850;
		y = (350 * sin(ang)) + 500;
		obj[n].setposition(x, y);
		this->player_s.push(obj[n]);
		ang = ang + ang2;
		n++;
	}
}
void Game::render_back()
{
	this->window->draw(this->bAck_gr);
}
void Game::Run()
{
	this->track.play();
	while (this->window->isOpen())
	{
		this->window->clear();
		this->Render();
		this->Update();
		this->window->display();
	}
}
void Game::Update()
{
	Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (ev.KeyPressed && ev.key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}		
	}
	if (ev.KeyPressed && ev.key.code == sf::Keyboard::A)
	{
		this->back_end(this->skips);
	}
}
void Game::Render()
{
	int n = 0;
	this->render_back();
	while (n!=this->no_players)
	{
		this->player_s.front().render(*this->window);
		this->player_s.push(this->player_s.front());
		this->player_s.pop();
		n++;
	}
}

void Game::back_end(int n)
{
	if (this->player_s.size() != 1)
	{
		bool ifkilled = false;
		while (!ifkilled)
		{
			if (this->count == n - 1)
			{
				this->player_s.pop();
				this->count = 0;
				ifkilled = true; 
			}
			else
			{
				this->player_s.push(this->player_s.front());
				this->player_s.pop();
				this->count++;
			}
		}

	}
	else
	{
		this->window->close();
	}
}


Player::Player()
{
	this->pos.x = 0;
	this->pos.y = 0;
	this->tex.loadFromFile("forpro.png");
	this->sprite.setTexture(this->tex);
	this->sprite.setScale(0.3f, 0.3f);
}

void Player::render(RenderTarget& target)
{
	target.draw(this->sprite);
}

void Player::update(bool flag)
{
	if (flag == 0)
	{
		this->pos.x = this->pos.x + 10.f;
		this->setposition(this->pos.x, this->pos.y);
	}
	else
	{
		this->pos.x = this->pos.x - 10.f;
		this->setposition(this->pos.x, this->pos.y);
	}
}

void Player::setposition(float posx, float posy)
{
	this->pos.x = posx;
	this->pos.y = posy;
	this->sprite.setPosition(pos);
}
int main()
{
	int n = 2;
	menu();
	cin >> n;
	while (n != 3) {
		if (n == 1)
		{
			cout << "To kill The Soldiers press A" << endl;
		}
		else if (n == 2)
		{
			cout << "How Many Soldiers you want to kill" << endl;
			cin >> n;
			int k;
			cout << "Enter the number of soldiers" << endl;
			cin >> k;
			Game obj(k, n);
			obj.Run();
		}
		cout << "You want to continue" << endl;
		cin >> n;
	}
}





