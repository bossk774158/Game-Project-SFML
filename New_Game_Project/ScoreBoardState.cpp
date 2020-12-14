#include "ScoreBoardState.h"


void ScoreBoardState::initFont()
{
    if (!this->font_number2.loadFromFile("Fonts/novem___.ttf"))
    {
        throw("Error to download font");
    }
}

ScoreBoardState::ScoreBoardState(RenderWindow* window, Font& font, Event* ev)
    :font_number(font), ev(ev)
{
    this->initFont();
    this->player_score = 0;
    this->total_time = 0.f;
    this->cursor_show = true;

    /// Init Background ///
    this->bg.setSize(
        Vector2f(
            static_cast<float>(window->getSize().x),
            static_cast<float>(window->getSize().y)
        )
    );
    this->bg.setFillColor(Color(20, 20, 20, 100));

    /// Init button container ///
    this->container.setSize(
        Vector2f(
            static_cast<float>(window->getSize().x) / 2.f,
            static_cast<float>(window->getSize().y - 60.f)
        )
    );
    this->container.setFillColor(Color(20, 20, 20, 200));
    this->container.setPosition(
        static_cast<float>(window->getSize().x) / 2.f - this->container.getSize().x / 2.f,
        30.f
    );

    /// Init Text ///
    this->menu_text.setFont(font_number2);
    this->menu_text.setCharacterSize(40);
    this->menu_text.setFillColor(Color(255, 255, 255, 200));
    this->menu_text.setString("Score Board");
    this->menu_text.setPosition(
        this->container.getPosition().x + this->container.getSize().x / 2 - this->menu_text.getGlobalBounds().width / 2,
        this->container.getPosition().y + 30.f
    );

    /// Init Name && Score Text ///
    for (int i = 0; i < 5; i++) {
        this->name_text[i].setFont(font_number2);
        this->name_text[i].setFillColor(Color(255, 255, 255, 200));
        this->name_text[i].setString(this->name[i]);
        this->name_text[i].setPosition(
            this->container.getPosition().x + 40.f,
            this->container.getPosition().y + 120.f + 50.f * i
        );
    }

    for (int i = 0; i < 5; i++) {
        this->score_text[i].setFont(font_number2);
        this->score_text[i].setFillColor(Color(255, 255, 255, 200));
        this->score_text[i].setString(to_string(this->score[i]));
        this->score_text[i].setPosition(
            this->container.getPosition().x + this->container.getSize().x - this->score_text[i].getGlobalBounds().width - 30,
            this->container.getPosition().y + 120.f + 50.f * i
        );
    }

}

ScoreBoardState::~ScoreBoardState()
{
    auto i = this->buttons.begin();
    for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
    {
        delete i->second;
    }
}

map<string, gui::Button*>& ScoreBoardState::get_buttons()
{
    return this->buttons;
}

const bool ScoreBoardState::is_button_pressed(const string key)
{
    if (this->input.length() > 0) {
        return this->buttons[key]->isPressed();
    }
    else
    {
        return this->buttons[key]->isPressed();
    }

    return false;
}

void ScoreBoardState::set_player_score(int player_score)
{
    this->player_score = player_score;
}


void ScoreBoardState::add_button(const string key, float y, float width, float height, const string text)
{
    float x = this->container.getPosition().x + this->container.getSize().x / 2 - width / 2;

    this->buttons[key] = new gui::Button(x, y, width, height,
        &this->font_number, text, 50,
        Color(255, 255, 255, 150), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
        Color(70, 70, 70, 200), Color(150, 150, 150, 200), Color(20, 20, 20, 200),
        Color(255, 255, 255, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50)
    );
}

void ScoreBoardState::check_score(string path)
{
    ///----- Show HighScore -----\\\

    /// Set Score ///
    for (int i = 0; i < 6; i++) {
        this->name[i] = "NOOB";
    }

    for (int i = 0; i < 6; i++) {
        this->score[i] = -999;
    }

    this->current_score = this->player_score;

    /// Read ///
    ifstream ifs(path);

    if (ifs.is_open()) {
        for (int i = 0; i < 5; i++) {
            ifs >> this->name[i];
            ifs >> this->score[i];
        }
    }
    ifs.is_open();

    /// Check Score 
    this->score_pos = 5;

    int k = 0;
    while (this->current_score <= this->score[k] && k <= 4) {
        k++;
    }

    if (k <= 4) {
        cout << k << "\n";
        this->score_pos = k;

        ///  Sort ///
        for (int i = 4; i > k; i--) {
            /// Sort Score ///
            this->score[i] = this->score[i - 1];

            /// Sort Name ///
            this->name[i] = this->name[i - 1];
        }

        this->score[this->score_pos] = this->current_score;

        /// Can be in high score ///
        if (this->score_pos <= 4) {
            ///  Name_Input_box ///
            this->name_input_bg.setSize(Vector2f(200.f, 30.f));
            this->name_input_bg.setPosition(this->container.getPosition().x + 40.f, this->container.getPosition().y + 80.f + 50.f * this->score_pos);

            this->name_input_cursor.setSize(Vector2f(5.f, 26.f));
            this->name_input_cursor.setPosition(Vector2f(this->container.getPosition().x + 42.f, this->container.getPosition().y + 80.f + 50.f * this->score_pos + 3.f));
            this->name_input_cursor.setFillColor(Color::Black);

            this->text_input.setFont(font_number);
            this->text_input.setCharacterSize(20);
            this->text_input.setFillColor(Color::Black);
            this->text_input.setPosition(this->name_input_bg.getPosition());
        }

        this->name_text[score_pos].setString(this->name[score_pos]);
        this->score_text[score_pos].setString(to_string(this->score[score_pos]));
    }

    for (int i = 0; i < 5; i++) {
        this->name_text[i].setString(this->name[i]);
        this->score_text[i].setString(to_string(this->score[i]));

        this->name_text[i].setPosition(
            this->container.getPosition().x + 40.f,
            this->container.getPosition().y + 80.f + 50.f * i
        );

        this->score_text[i].setPosition(
            this->container.getPosition().x + this->container.getSize().x - this->score_text[i].getGlobalBounds().width - 30,
            this->container.getPosition().y + 80.f + 50.f * i
        );
    }
}

void ScoreBoardState::save_high_score(string path)
{
    this->name[this->score_pos] = this->input;

    /// Write ///
    ofstream ofs(path);

    if (ofs.is_open()) {
        for (int i = 0; i < 5; i++) {
            ofs << this->name[i] << " ";
            ofs << this->score[i] << "\n";

        }
    }
    ofs.is_open();
}

void ScoreBoardState::update(const sf::Vector2i& mousePosWindow)
{
    for (auto& i : this->buttons) {
        i.second->update(mousePosWindow);
    }

    /// Input Name ////
    if (this->ev->type == Event::EventType::TextEntered)
    {
        if (this->ev->text.unicode != 13) {
            if (this->ev->text.unicode != this->last_char && this->ev->text.unicode == 8 && this->input.length() > 0) {
                this->last_char = this->ev->text.unicode;
                this->input.erase(this->input.length() - 1);
                this->text_input.setString(this->input);
                this->name_input_cursor.setPosition(this->name_input_bg.getPosition().x + this->text_input.getGlobalBounds().width + 5, this->name_input_bg.getPosition().y + 2.f);
            }
            else if (this->last_char != this->ev->text.unicode && this->ev->text.unicode != 8) {
                //cout << this->ev->text.unicode << endl;
                this->last_char = this->ev->text.unicode;
                this->input += this->ev->text.unicode;
                this->text_input.setString(this->input);
                this->name_input_cursor.setPosition(this->name_input_bg.getPosition().x + this->text_input.getGlobalBounds().width + 5, this->name_input_bg.getPosition().y + 2.f);
                cout << this->input << endl;
            }
        }
    }
    else if (this->ev->type == Event::EventType::KeyReleased && last_char != ' ') {
        this->last_char = ' ';
    }
    
}

void ScoreBoardState::update(const float& dt)
{
    
}

void ScoreBoardState::render(RenderTarget& target)
{
    target.draw(this->container);

    for (auto& i : this->buttons) {
        i.second->render(target);
    }

    target.draw(this->menu_text);

    for (int i = 0; i < 5; i++) {
        if (i != this->score_pos) {
            target.draw(this->name_text[i]);
        }
        else {
            /// Input Name ///
            target.draw(this->name_input_bg);

            this->total_time += clock.restart().asSeconds();
            if (this->total_time >= 0.5) {
                this->total_time = 0;
                this->cursor_show = !this->cursor_show;
            }

            if (this->cursor_show) {
                target.draw(this->name_input_cursor);
            }

            target.draw(this->text_input);
        }

        target.draw(this->score_text[i]);
    }
}