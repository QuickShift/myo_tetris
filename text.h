#pragma once

#include <SDL2/SDL_ttf.h>
#include <stdio.h>

TTF_Font*
LoadFont(char* FontName, u32 FontSize)
{
    TTF_Font* Result;
    Result = TTF_OpenFont(FontName, FontSize);
    if(!Result)
    {
        printf("ERROR: Count not create font!\n%s\n", SDL_GetError());
        return 0;
    }
    return Result;
}

SDL_Texture*
CreateTextTexture(SDL_Rect* TextRectangle, SDL_Renderer* Renderer, TTF_Font* Font, char* Text)
{
    SDL_Surface* TextSurface;

    SDL_Color FontColor = {};
    FontColor.a = 255;
    FontColor.r = 255;
    FontColor.g = 255;
    FontColor.b = 255;

    TextSurface = TTF_RenderUTF8_Blended(Font, Text, FontColor);
    if(!TextSurface)
    {
        printf("ERROR: Could not create TextSurface\n%s\n", SDL_GetError());
        return 0;
    }

    if(TextRectangle)
    {
        TextRectangle->w = TextSurface->w;
        TextRectangle->h = TextSurface->h;
    }

    SDL_Texture* TextTexture;
    TextTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
    SDL_FreeSurface(TextSurface);
    return TextTexture;
}
