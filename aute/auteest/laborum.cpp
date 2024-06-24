void onSwipeRight() {
  if (player_state_ == PlayerState::kPlaying) {
    seek_to(std::max(0.0, current_position_ - 10.0));
  }
}  
