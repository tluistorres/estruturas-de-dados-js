console.log("Versão 2.0: Corações Coloridos Ativada!"); // Para você conferir no F12

const canvas = document.getElementById('fireworksCanvas');
const ctx = canvas.getContext('2d');

let audioCtx = null;
let particles = [];
let fireworks = [];

function resize() {
    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;
}
window.addEventListener('resize', resize);
resize();

function playHeartSound() {
    if (!audioCtx) return;
    if (audioCtx.state === 'suspended') audioCtx.resume();
    const osc = audioCtx.createOscillator();
    const gain = audioCtx.createGain();
    osc.type = 'triangle'; 
    osc.frequency.setValueAtTime(180, audioCtx.currentTime);
    osc.frequency.exponentialRampToValueAtTime(0.01, audioCtx.currentTime + 0.6);
    gain.gain.setValueAtTime(0.4, audioCtx.currentTime);
    gain.gain.exponentialRampToValueAtTime(0.01, audioCtx.currentTime + 0.6);
    osc.connect(gain);
    gain.connect(audioCtx.destination);
    osc.start();
    osc.stop(audioCtx.currentTime + 0.6);
}

window.addEventListener('click', () => {
    if (!audioCtx) {
        audioCtx = new (window.AudioContext || window.webkitAudioContext)();
        document.getElementById('ui').style.opacity = '0';
        setTimeout(() => document.getElementById('ui').style.display = 'none', 500);
    }
});

class Firework {
    constructor() {
        this.x = Math.random() * canvas.width;
        this.y = canvas.height;
        this.targetY = Math.random() * (canvas.height / 2.5) + 50;
        
        // ESTA LINHA GERA CORES DIFERENTES (0 a 360 graus no círculo cromático)
        this.hue = Math.floor(Math.random() * 360); 
        this.color = `hsl(${this.hue}, 100%, 60%)`; 
        
        this.speed = 4;
    }
    // ... restante do código
}

    update() {
        this.y -= this.speed;
        if (this.y <= this.targetY) {
            this.explode();
            return true;
        }
        return false;
    }

    draw() {
        ctx.fillStyle = this.color;
        ctx.beginPath();
        ctx.arc(this.x, this.y, 3, 0, Math.PI * 2);
        ctx.fill();
    }

    explode() {
        playHeartSound();
        const steps = 100; 
        for (let i = 0; i < steps; i++) {
            const t = (i / steps) * Math.PI * 2;
            const x = 16 * Math.pow(Math.sin(t), 3);
            const y = -(13 * Math.cos(t) - 5 * Math.cos(2*t) - 2 * Math.cos(3*t) - Math.cos(4*t));
            particles.push(new HeartParticle(this.x, this.y, x, y, this.hue));
        }
    }


class HeartParticle {
    constructor(x, y, vx, vy, hue) {
        this.x = x;
        this.y = y;
        this.vx = vx * 0.5; 
        this.vy = vy * 0.5;
        this.hue = hue;
        this.life = 120;
        this.opacity = 1;
    }

    update() {
        this.x += this.vx;
        this.y += this.vy;
        this.vy += 0.04; 
        this.life--;
        this.opacity = this.life / 120;
    }

    draw() {
        ctx.save();
        ctx.globalAlpha = this.opacity;
        ctx.fillStyle = `hsl(${this.hue}, 100%, 60%)`;
        ctx.beginPath();
        ctx.arc(this.x, this.y, 2, 0, Math.PI * 2);
        ctx.fill();
        ctx.restore();
    }
}

function animate() {
    ctx.fillStyle = 'rgba(0, 0, 0, 0.15)';
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    if (Math.random() < 0.04) fireworks.push(new Firework());
    fireworks = fireworks.filter(f => { f.draw(); return !f.update(); });
    particles = particles.filter(p => { p.update(); p.draw(); return p.life > 0; });
    requestAnimationFrame(animate);
}
animate();



// Dentro da pasta projeto_coracao, executar o código:

// Executar o servidor : npx http-server

// Ctrl + Shift + N

// Digitar o link http://127.0.0.1:8080

// Digitar npx http-server -c-1 para nunca guardar o cache