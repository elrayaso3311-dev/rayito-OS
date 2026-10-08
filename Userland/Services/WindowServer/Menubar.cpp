/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, sin-ack <sin-ack@protonmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Menubar.h"
#include "WindowManager.h"

namespace WindowServer {

void Menubar::layout_menu(Menu& menu, Gfx::IntRect screen_rect)
{
    // Margen adaptado al estilo moderno y limpio de macOS Catalina
    static constexpr auto menubar_menu_margin = 16;
    static constexpr auto menubar_height = 28; // Altura fija de la barra superior estilo Mac

    auto& wm = WindowManager::the();
    
    // Adaptamos el cálculo para que la barra ocupe la parte superior global de la pantalla
    // en lugar de depender de una ventana individual (window_rect).
    int text_width = wm.font().width(Gfx::parse_ampersand_string(menu.name()));
    
    // Posicionamos los menús de forma secuencial en la barra superior global
    menu.set_rect_in_window_menubar({ m_next_menu_location.x(), 0, text_width + menubar_menu_margin, menubar_height });
    
    // Desplazamos el puntero para el siguiente menú en la barra
    m_next_menu_location.translate_by(menu.rect_in_window_menubar().width(), 0);
}

}